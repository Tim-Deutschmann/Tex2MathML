version=0.1

# DEBUG	= -g -fverbose-asm -masm=intel
DEBUG	= -g
WARN	= -pedantic -W -Wall -Wno-format -Wno-unused-parameter
INCLUDE = -I .

target = linux_amd64

CC	= g++
DEFINES = -DVERSION=\"${version}\"
obj_ending=o
ending=

# LDFLAGS	= -lefence
# LDFLAGS	= -std=c++11
LDFLAGS	=

# CFLAGS	= -c ${WARN} ${DEFINES} -std=c++11 -lefence
#CFLAGS	= -c ${WARN} ${DEFINES} -std=c++11
CFLAGS	= -c ${WARN} ${DEFINES}

export
