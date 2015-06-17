# 单词游戏 第三版

## 编译运行说明

本程序在 OS X 10.10.3 ，编译器 Apple LLVM version 6.1.0 (clang-602.0.49) (based on LLVM 3.6.0svn) 测试编译通过，Windows 下可能存在少数问题。

依赖于Qt 5.3 +，所以编译时必须安装好 Qt 的 SDK。

可以使用 Qt creator 打开项目文件 （服务器端和客户端分别为 server.pro 和 client.pro ），编译运行。

也可以使用 cmake 编译运行，但需要在 CmakeLists.txt 中指定 Qt 的 SDK 目录！

## 文档结构

```
├── CMakeLists.txt # cmake 配置文件
├── README.md # 说明文档
├── client # 客户端代码
│   ├── CMakeLists.txt
│   ├── client.pro # Qt 项目配置文件
│   ├── main.cpp
│   └── src #代码目录
│       ├── controller
│       │   ├── app.cpp
│       │   ├── app.h
│       │   ├── board.cpp
│       │   ├── board.h
│       │   ├── game.cpp
│       │   └── game.h
│       ├── model
│       │   ├── Model.cpp
│       │   ├── Model.h
│       │   ├── Player.cpp
│       │   ├── Player.h
│       │   ├── Question.cpp
│       │   ├── Question.h
│       │   ├── User.cpp
│       │   └── User.h
│       ├── service
│       │   ├── ClientService.cpp
│       │   └── ClientService.h
│       └── util
│           ├── Console.h
│           └── rlutil.h
└── server #服务器端代码目录
    ├── CMakeLists.txt
    ├── main.cpp
    ├── server.pro
    ├── server.pro.user
    └── src
        ├── controller
        │   ├── Server.cpp
        │   └── Server.h
        ├── model
        │   ├── Connection.cpp
        │   ├── Connection.h
        │   ├── Model.h
        │   ├── Player.cpp
        │   ├── Player.h
        │   ├── Question.cpp
        │   ├── Question.h
        │   ├── Referee.cpp
        │   ├── Referee.h
        │   ├── User.cpp
        │   └── User.h
        ├── service
        │   ├── ServerService.cpp
        │   └── ServerService.h
        └── util
            ├── Console.h
            └── rlutil.h
```


## 代码框架

### 客户端

客户端设计与第一版、第二版基本相同，使用了 MVC 的设计架构。具体就是：Model 抽象好数据类型（用户与题目），数据的控制与交互交给 Controller 处理。但是不同的是，移除了『获取数据的部分』，这部分交给  ClientServer 处理。

ClientServer 是一个『Service』，通过 ClientServer::getInstance() 实现了单例模式，即项目中任何一个部分都可以调用这个单例对象。这个对象封装好了 Socket 对象，实现与数据库的交互。

Socket 的数据流操作本来是一个『异步 IO』过程，但是考虑到客户端同服务端的交流问题，我把它改成了一个同步过程，即：发送数据时瞬间发送，如果需要响应，则阻塞等待。通过 Qt 本身的 EventLoop 就可以很方便的过渡交互。事实上，和第一版的代码也没有太多变动，只是状态自动机稍微改变了一下，在每个 Controller 内部，通过 responseHandler() 处理服务器返回的数据，并且控制状态转换方向。

### 服务端

服务端整体功能是提供一个 Web API，只需要根据客户端的请求，给出具体的响应即可。所以设计上也很简单，监听客户端的数据，然后调用响应的 Controller 去处理。Model 方面则沿用了第一版、第二版的代码，完成模型与数据库之间的交互。

具体的 API实现，使用了 JSON 作为其数据载体，收到数据判断 "type" 键，然后交给对应的 Controller 去处理。使用 JSON 可以方便数据流 的交换，简化读取的麻烦。

同样，服务端通过一个单例对象『ServerService』，完成服务器操作，不同的是，增加了和『room』有关的部分，即可以对客户端进行组播，方便完成题目的需求。

## 问题

第三版的代码编写过程中，也发现了设计上的几个逻辑问题，在此说明以下：

1. Model 设计有点问题；

	第一版、第二版中，Model 可以自己管理数据，也就是说，对数据的存储过程都是在 Model 内部进行的。这样，固然前两版可以完成需求，但是放在第三版就有点麻烦，因为这样是 **紧耦合** 的。第三版中，服务器端和客户端的数据流很明显是不一样的，虽然方法几乎一模一样，但是所无法重用了……只是再改可以有点麻烦，所以在此说下我认为的正确的设计。

	![](/Users/nil/Documents/Workspace/school/v3/untitled.png)

	如图所示，Model 内部需要实例化一个实现了『DataStore』接口的成员，这个成员如果是『DatabaseManager』，即实现了与数据库的连接，就可以在 Server 端使用，如果是『SocketDataManager』，就可以在 Client 端使用，更重要的是，仅仅除了这个成员不同，其余的方法和属性都是一样的！！这意味着基本可以在 C 端和 S 端重用 Model 代码。

2. Client 端 Controller 代码复用

	Client 端的 Controller 基本是复用了之前的代码，但是还没有完全复用。如果把前面说的 Model 问题改掉，让 Controller 只与 Model 进行交互，ClientServerive 作为 Model 的数据提供者，那么之前的代码几乎不需要做任何变化就可以复用到第三版里面。