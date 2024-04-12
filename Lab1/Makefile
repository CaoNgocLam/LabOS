CC=gcc 
TARGET=calc
OBJ= base_cal.o calc.o hist_management.o
DEPS=calc.h
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ)

$.o : $.c DEPS 
	$(CC) -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJ)