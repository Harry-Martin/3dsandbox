
.PHONY = all clean test

CC := gcc

LIBS := -lm -lllama -lGL -lglfw -lGLEW
CFLAGS := 

SRC_DIR := src
BUILD_DIR := build

SRC := ${wildcard ${SRC_DIR}/*.c}
OBJ := ${patsubst ${SRC_DIR}/%.c, ${BUILD_DIR}/%.o, ${SRC}}

EXE := test

all: ${EXE}

${EXE}: ${OBJ}
	${CC} -o ${EXE} ${OBJ} ${LIBS}

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	rm ${EXE} ${OBJ}
