<p align="center">
<img src=https://github.com/RandyGaul/cute_framework/blob/master/assets/CF_Banner_Hifi_1280.png>
<br>
<br>
<img alt="GitHub Workflow Status" src="https://img.shields.io/github/actions/workflow/status/randygaul/cute_framework/build.yml">
<img alt="Discord" src="https://img.shields.io/discord/432009046833233930?label=discord">
</p>

[Cute Framework](https://randygaul.github.io/cute_framework/#/) (CF for short) is the *cutest* framework available for making 2D games in C++. CF provides a portable foundational layer for building 2D games in C/C++ without baggage, gnarly dependencies, or cryptic APIs. CF runs almost anywhere, including Windows, MacOS, iOS, Android, Linux, and more!

## Download and Setup

The easiest option is to head over and pickup the [latest pre-built version](https://github.com/randygaul/cute_framework/releases/latest) of Cute Framework. You can link your project against Cute Framework as either a static or shared library. Be sure to also visit the [Cute Framwork documentation site](https://randygaul.github.io/cute_framework/#/).

### Building from Source

Another option for those familiar with CMake is to build Cute Framework from source with CMake.

1. Download and install CMake v3.14+ (for easy cross-platform building)
2. Copy + paste [CMakeLists.txt](https://github.com/RandyGaul/cute_framework_project_template/blob/main/CMakeLists.txt) from the [CF project template](https://github.com/RandyGaul/cute_framework_project_template). Find + replace "my_project_name".
3. Run CMake on your project folder. Cmake will automagically download and hook up CF.
4. Use the below code snippet for your first `main.cpp`!

## Example Game Window

> Creating a window and closing it.

```cpp
#include <cute.h>
using namespace Cute;

int main(int argc, char* argv[])
{
	// Create a window with a resolution of 640 x 480.
	int options = APP_OPTIONS_DEFAULT_GFX_CONTEXT | APP_OPTIONS_WINDOW_POS_CENTERED;
	Result result = make_app("Fancy Window Title", 0, 0, 640, 480, options, argv[0]);
	if (is_error(result)) return -1;

	while (app_is_running())
	{
		app_update();
		// All your game logic and updates go here...
		app_draw_onto_screen();
	}

	destroy_app();

	return 0;
}
```

# Resources

The [Cute Framework documentation website](https://randygaul.github.io/cute_framework/#/) is the go-to place for finding all the resources available. Here are some quick-links to get you started:

- [Topics and Tutorials](https://randygaul.github.io/cute_framework/#/topics_and_tutorials)
- [Samples](https://randygaul.github.io/cute_framework/#/samples)
- [API Reference](https://randygaul.github.io/cute_framework/#/api_reference)

If you're stuck and need help then check out the [Discord chat](https://discord.gg/2DFHRmX). Feel free to pop in and ask questions, make suggestions, or have a discussion. General gamedev chatting unrelated to CF is also welcome!

Feel free to open up an [issue right here on GitHub](https://github.com/RandyGaul/cute_framework/issues) to ask any questions. If you'd like to make a pull request I highly recommend opening a GitHub issue first to start a discussion on any changes you would like to make.

<p align="center"><img src=https://github.com/RandyGaul/cute_framework/blob/master/assets/CF_Logo_Pixel_2x.png></p>
