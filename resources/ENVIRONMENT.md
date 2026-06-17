# SYSTEM DESCRIPTION/REFERENCE

```
Architecture:                x86_64
  CPU op-mode(s):            32-bit, 64-bit
  Address sizes:             39 bits physical, 48 bits virtual
  Byte Order:                Little Endian
CPU(s):                      4
  On-line CPU(s) list:       0-3
Vendor ID:                   GenuineIntel
  Model name:                11th Gen Intel(R) Core(TM) i7-1185G7 @ 3.00GHz
    CPU family:              6
    Model:                   140
    Thread(s) per core:      1
    Core(s) per socket:      4
    Socket(s):               1
    Stepping:                1
    Microcode version:       0xbe
    BogoMIPS:                5990.40
    Flags:                   fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clfl
                             ush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm con
                             stant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpui
                             d aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx smx est
                             tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc
                             _deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fa
                             ult epb cat_l2 cdp_l2 ssbd ibrs ibpb stibp ibrs_enhanced tpr_shadow flexprio
                             rity ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid rd
                             t_a avx512f avx512dq rdseed adx smap avx512ifma clflushopt clwb intel_pt avx
                             512cd sha_ni avx512bw avx512vl xsaveopt xsavec xgetbv1 xsaves split_lock_det
                             ect user_shstk dtherm arat pln pts vnmi avx512vbmi umip pku ospke avx512_vbm
                             i2 gfni vaes vpclmulqdq avx512_vnni avx512_bitalg tme avx512_vpopcntdq rdpid
                              movdiri movdir64b fsrm avx512_vp2intersect md_clear ibt flush_l1d arch_capa
                             bilities
Virtualization features:
  Virtualization:            VT-x
Caches (sum of all):
  L1d:                       192 KiB (4 instances)
  L1i:                       128 KiB (4 instances)
  L2:                        5 MiB (4 instances)
  L3:                        12 MiB (1 instance)
NUMA:
  NUMA node(s):              1
  NUMA node0 CPU(s):         0-3
```

CORE 3 Performance
L1 Cache: 88116.1 MB/sec | sudo ./mlc --loaded_latency -b19 -m0x08
L2 Cache: 54024.6 MB/sec | sudo ./mlc --loaded_latency -b400 -m0x08
L3 Cache: 37443.1 MB/sec | sudo ./mlc --loaded_latency -b8m -m0x08

