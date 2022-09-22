transcript on
if ![file isdirectory verilog_libs] {
	file mkdir verilog_libs
}

vlib verilog_libs/altera_ver
vmap altera_ver ./verilog_libs/altera_ver
vlog -vlog01compat -work altera_ver {e:/altera/13.0/quartus/eda/sim_lib/altera_primitives.v}

vlib verilog_libs/lpm_ver
vmap lpm_ver ./verilog_libs/lpm_ver
vlog -vlog01compat -work lpm_ver {e:/altera/13.0/quartus/eda/sim_lib/220model.v}

vlib verilog_libs/sgate_ver
vmap sgate_ver ./verilog_libs/sgate_ver
vlog -vlog01compat -work sgate_ver {e:/altera/13.0/quartus/eda/sim_lib/sgate.v}

vlib verilog_libs/altera_mf_ver
vmap altera_mf_ver ./verilog_libs/altera_mf_ver
vlog -vlog01compat -work altera_mf_ver {e:/altera/13.0/quartus/eda/sim_lib/altera_mf.v}

vlib verilog_libs/altera_lnsim_ver
vmap altera_lnsim_ver ./verilog_libs/altera_lnsim_ver
vlog -sv -work altera_lnsim_ver {e:/altera/13.0/quartus/eda/sim_lib/altera_lnsim.sv}

vlib verilog_libs/cycloneii_ver
vmap cycloneii_ver ./verilog_libs/cycloneii_ver
vlog -vlog01compat -work cycloneii_ver {e:/altera/13.0/quartus/eda/sim_lib/cycloneii_atoms.v}

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/add_v.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/add_b.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/polar.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/change.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/HDB3.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/m_sequence.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/even_div16.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/even256_div.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/delvb.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/trans8to1.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/findv.v}
vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3 {E:/altera/13.0/PRJECT/HDB3/recover.v}

vlog -vlog01compat -work work +incdir+E:/altera/13.0/PRJECT/HDB3/simulation/modelsim {E:/altera/13.0/PRJECT/HDB3/simulation/modelsim/HDB3.vt}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneii_ver -L rtl_work -L work -voptargs="+acc"  HDB3_vlg_tst

add wave *
view structure
view signals
run -all
