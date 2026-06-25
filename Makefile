CC ?= cc
CFLAGS ?= -std=c2x -Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer -mavx2 -Wpadded
OPTLVL ?= -O3
LDFLAGS ?=
LDLIBS ?= -lm

SRCDIR := ./src
OUTDIR := ./target
OUT := $(OUTDIR)/1brc.out

C_SRCS += $(SRCDIR)/main.c \
		  $(SRCDIR)/parsing.c \
		  $(SRCDIR)/hash_table.c

INC += -Iinc/

.PHONY: all clean

all: $(OUT)

$(OUT): $(C_SRCS) | $(OUTDIR)
	$(CC) $(CFLAGS) $(INC) $(OPTLVL) $(LDFLAGS) -o $@ $(C_SRCS) $(LDLIBS)

$(OUTDIR):
	mkdir -p $@


clean:
	rm -rf $(OUTDIR)
