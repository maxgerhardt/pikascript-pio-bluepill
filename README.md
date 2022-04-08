# PikaScript Bluepill Demo

## Description

Uses the sources from http://pikascript.com/ for stm32f103c8, with all versions set to "latest". See https://github.com/pikasTech/pikascript.

Code adaptions based on https://github.com/pikasTech/pikascript-demo-stm32/tree/main/stm32f103c8t6/01-demo-pikascript-stm32f103c8t6-led.

And makes it a PlatformIO-compilable project, meaning you can install VSCode + PlatformIO extension (https://platformio.org/install/ide?install=vscode) and open the project and debug as normal.

The project opens a PikaScript shell on the UART console by calling into `pikaScriptShell()`. 

```cpp
  pikaMain = pikaScriptInit();
  // add special LED object to it
  obj_newObj(pikaMain, "led", "LED", New_LED);

  // start shell and stay there
  printf("Launching PikaScript shell.\r\n");
  pikaScriptShell(pikaMain);
```

## Media

![debug](debug.png)

## Output

At 115200 baud at TX = PA9. RX (PA10) is unused.

```
  pikaMain = pikaScriptInit();
  // add special LED object to it
  obj_newObj(pikaMain, "led", "LED", New_LED);

  // print some debug info after basic init
  printf("memory used now: %d B\r\n", pikaMemNow());
  printf("memory used max: %d B\r\n", pikaMemMax());

  // start shell and stay there
  printf("Launching PikaScript shell.\r\n");
  pikaScriptShell(pikaMain);
>>> 
```

There is the special built-in `led` object that the firmware creates with `on()` and `off()` methods.

```
>>> led.on()
>>> led.off()
```

Basic Python-like commands can be executed

```
>>> 1 + 1
2
>>> 1.2 + 3.3
4.500000
>>> 2 ** 8
256.000000
>>> print("Hello" + " world")
Hello world
```

Special libraries can be imported as seen e.g. in the [example](https://github.com/pikasTech/pikascript/blob/master/examples/GPIO/main.py).

```
>>> import PikaStdLib
>>> import machine
>>> mem = PikaStdLib.MemChecker()
>>> mem.max()
1.89 kB
>>> mem.now()
1.00 kB
>>>
```

Some aspects don't yet seem to work though: https://github.com/pikasTech/pikascript/issues