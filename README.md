# 单词游戏 第一版 文档

## 运行说明

该项目基于 Qt 构建，请使用 Qt 5 以上 SDK 运行。此外，配置了不完全的 cmake 文件，推荐使用 CLion 修改。

## 目录结构

```
├── CMakeLists.txt # CMAKE 配置文件
├── README.md
├── WordsGameConsole.pro # Qt 项目文件
├── lib
│   └── rlutil.h # 第三方依赖，用于处理CLI
├── main.cpp # 入口函数
└── src # 模块代码文件夹
    ├── controller # 控制器目录
    │   ├── app.cpp
    │   ├── app.h
    │   ├── board.cpp
    │   ├── board.h
    │   ├── game.cpp
    │   └── game.h
    ├── model # 模型目录
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
    └── utils # 工具方法目录
        └── Console.h
```

## 代码设计

代码设计上采用了『MVC』的设计模式，Model 负责数据的存储，数据模型的抽象（包括方法，等），Controller 负责模型的控制，在我的代码中也肩负对 CLI 的操作（即 View 的功能）。

### Model

#### Model 模板类

Model 模板类是对 『模型』的抽象，负责所有和模型有关的增删改查的操作。

Model 是一个模板类，如果需要新建一个模型，需要这个模型去继承以这个模型为模板的类（比如 class User : public Model<User>），即 CRTP。然后 配置 Model<User> 类的 fiedls，primaryKey，即可。

#### User 类

User 类是对『用户』的抽象，继承自 Model，同时具有用户的公共方法，比如注册，登录。

#### Player 类

Player 类继承自 User 类，是对『玩家』的抽象，增加了玩家的方法，比如升级，等。

#### Referee 类

Referee 类继承自 User 类，是对『出题者』的抽象，增加了出题者的方法，比如出题，等。

#### Question 类

Question 是对『题目』的抽象，继承自 Model。


### Controller

#### App

App 控制器是核心控制器，包含了用户注册，登录，等核心流程。

#### Game

Game 控制器是控制游戏进程的控制器。

#### Board

Board 控制器是控制展板的控制器。

### Util

#### Console

封装了第三方依赖『rlutil』
