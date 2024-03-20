Import("env")

#
# Dump build environment (for debug)
# print(env.Dump())
#

env.Append(
  LINKFLAGS=[
              #"-u_printf_float",
              #"-u_scanf_float",
              #"--specs=nosys.specs",
              #"--specs=nano.specs"
#      "-static",
#      "-static-libgcc",
#      "-static-libstdc++"
  ]
)