Import("env")
env.Append(LINKFLAGS=["--specs=nano.specs"])
env.Append(LIBS=["nosys"])