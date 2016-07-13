# Copyright (C) 2008-2015 Marvell International Ltd.
# All Rights Reserved.

exec-y += testrig
testrig-objs-y := src/main.c
# Applications could also define custom linker files if required using following:
#testrig-ld-y := /path/to/ldscript
# Applications could also define custom board files if required using following:
#testrig-board-y := /path/to/boardfile
