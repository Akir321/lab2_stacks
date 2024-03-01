CC = gcc
CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline\
 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default\
 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy\
 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op\
 -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual\
 -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG\
 -D_EJUDGE_CLIENT_SIDE 

INC_DIR  = includes/
SRC_DIR  = source/
OBJ_DIR  = object/

INCLUDES =  $(INC_DIR)stack_array.h 	 	\
			$(INC_DIR)stack_list.h   	 	\
			

OBJECTS  =  $(OBJ_DIR)stack_array.o 		\
			$(OBJ_DIR)stack_list.o   		\
		

all: test_stacks


test_stacks: $(OBJ_DIR)main_stacks.o  $(OBJECTS)
	$(CC) $(OBJECTS) $< -o $@ $(CC_FLAGS)


$(OBJ_DIR)stack_array.o : $(SRC_DIR)stack_array.cpp $(INC_DIR)stack_array.h
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(OBJ_DIR)stack_list.o : $(SRC_DIR)stack_list.cpp $(INC_DIR)stack_list.h
	$(CC) -c $< -o $@ $(CC_FLAGS)


.PHONY: clean

clean:
	rm $(OBJECTS) *.exe 