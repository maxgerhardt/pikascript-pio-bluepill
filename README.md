# PikaScript Bluepill Demo

## Description

Uses the sources from http://pikascript.com/ for stm32f103c8, with all versions set to "latest".

Code adaptions based on https://github.com/pikasTech/pikascript-demo-stm32/tree/main/stm32f103c8t6/01-demo-pikascript-stm32f103c8t6-led.

And makes it a PlatformIO-compilable project, meaning you can install VSCode + PlatformIO extension (https://platformio.org/install/ide?install=vscode) and open the project and debug as normal.

The project blinks the PC13 LED with a custom-made Python object that has its Python member methods bound to C functions.

The main loop runs Python code which in turn calls into the C bindings

```cpp
  PikaObj *root = newRootObj("root",New_MyRoot);
  while (1)
  {
    HAL_Delay(1000);
    obj_run(root, "led.on()");
    HAL_Delay(1000);
    obj_run(root, "led.off()");
  }
```

## Media

![debug](debug.png)

## Output

At 115200 baud at TX = PA9. RX (PA10) is unused.

```
memory used now: 40 B
memory used max: 192 B
```