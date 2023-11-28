CC     := cc
CFLAG  := -std=c99 -Wall -Wextra -O3
INC    := -Iinclude
LIB    :=
SRCDIR := src
OBJDIR := obj
SRCS   := $(shell find $(SRCDIR) -type f -name *.c)
OBJS   := $(patsubst %.c,obj/%.o,$(SRCS))
DEPS   := $(patsubst %.c,obj/%.d,$(SRCS))
OUTDIR := output
TARGET := a.out

help:
	@echo "all   : create \"$(TARGET)\""
	@echo "clean : remove \"$(TARGET)\" and object files under \"$(OBJDIR)\""
	@echo "help  : show this message"

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $@ $^ $(LIB)

$(OBJDIR)/%.o: %.c
	@if [ ! -e $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAG) -MMD $(INC) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) $(TARGET)

-include $(DEPS)

.PHONY : all clean help

