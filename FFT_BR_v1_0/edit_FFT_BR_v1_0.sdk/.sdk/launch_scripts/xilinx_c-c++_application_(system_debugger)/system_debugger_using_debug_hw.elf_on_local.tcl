connect -url tcp:127.0.0.1:3121
source C:/ip_repo/edit_FFT_BR_v1_0.sdk/design_1_wrapper_hw_platform_1/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Avnet MiniZed V1 1234-oj1A"} -index 0
loadhw -hw C:/ip_repo/edit_FFT_BR_v1_0.sdk/design_1_wrapper_hw_platform_1/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Avnet MiniZed V1 1234-oj1A"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Avnet MiniZed V1 1234-oj1A"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Avnet MiniZed V1 1234-oj1A"} -index 0
dow C:/ip_repo/edit_FFT_BR_v1_0.sdk/HW/Debug/HW.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Avnet MiniZed V1 1234-oj1A"} -index 0
con
