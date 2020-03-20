# Purezento

Purezento is a simple graphics libaray to draw simple objects and interactive it with commands. It is based imgui and Code-Red.

Thie project is only used for my alg-dat course design. It can provide some simple interface to draw simple objects. User only need to provide some callback functions to build a demo.

## Usage 

- Build simple demos with graphics.
- Draw some 2D objects with commands.

## Build

- Clone this repositoriy.
- Clone Code-Red to `References` folder. 
- Open `.sln` with Visual Studio 2019 and build it with x64.

## How to use

There are four core interface for user. There are `runtime`, `console`, `render`, `config`. Before you add callbacks to them, you should create a `runtime` instance. When you finished to add callbacks, you should call `runtime::run_loop` to start main loop of program.

```C++
auto runtime = std::make_shared<purezento::runtime>(...);

// add callbacks to console, render, config

runtime->run_loop();
```

You can use `runtime` to get other core interface.

### Console

Console is a window that user can input command and output some texts.

Console provide two public members. 

- `callbacks` : When you input a command, the console will find the callback that support this command and run it. It is a `std::map<std::string, callback>`. The first is the name of command, the second is the callback function.

- `texts` : The texts of console, if you want to add a text to console window, just use `push_back` to add text. It is a `std::vector<console_text>`, you also can erase or update texts by modifying the `texts`.

### Render

Render is a simple renderer to render simple objects. For example, circle, text, rectangle, triangle and so on.

Render provide two public members.

- `callbacks` : We will invoke them in the loop of program every time. You can use this callback function to update the `draw_elements`. It is a `std::vector<std::string, callback>`.

- `draw_elements` : Render lists indicate the elements we will render. It is a `std::map<std::string, std::vector<draw_element>>`. The first is a group name of `draw_elements` and the second is an array of `draw_element`.

### Config

Config is used to set some properties of program. For example, the width of line we render. 

Config provide a public members.

- `callbacks` : We will invoke them in the loop of program every time. User can use `imgui` to add some UI objects to config window.

