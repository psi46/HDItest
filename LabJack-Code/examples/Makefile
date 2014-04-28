#
# Makefile for U12 example programs
#

all: list-all analog digitalIO OurDigitalIO InitializeDigitalIO easyFunctions stream Poweron Clock0 Clock1 Clock2 Clock3 CTR0 CTR1 CTR2 CTR3 SDA0 SDA1 SDA2 SDA3 HVon

list-all: list-all.c
	$(CC) $< -o $@ -lljacklm

analog: analog.c
	$(CC) $< -o $@ -lljacklm

digitalIO: digitalIO.c
	$(CC) $< -o $@ -lljacklm

OurDigitalIO: OurDigitalIO.c
	$(CC) $< -o $@ -lljacklm

InitializeDigitalIO: InitializeDigitalIO.c
	$(CC) $< -o $@ -lljacklm

easyFunctions: easyFunctions.c
	$(CC) $< -o $@ -lljacklm

stream: stream.c
	$(CC) $< -o $@ -lljacklm

Poweron: Poweron.c
	$(CC) $< -o $@ -lljacklm

Clock0: Clock0.c
	$(CC) $< -o $@ -lljacklm

Clock1: Clock1.c
	$(CC) $< -o $@ -lljacklm

Clock2: Clock2.c
	$(CC) $< -o $@ -lljacklm

Clock3: Clock3.c
	$(CC) $< -o $@ -lljacklm

CTR0: CTR0.c
	$(CC) $< -o $@ -lljacklm

CTR1: CTR1.c
	$(CC) $< -o $@ -lljacklm

CTR2: CTR2.c
	$(CC) $< -o $@ -lljacklm

CTR3: CTR3.c
	$(CC) $< -o $@ -lljacklm

SDA0: SDA0.c
	$(CC) $< -o $@ -lljacklm

SDA1: SDA1.c
	$(CC) $< -o $@ -lljacklm

SDA2: SDA2.c
	$(CC) $< -o $@ -lljacklm

SDA3: SDA3.c
	$(CC) $< -o $@ -lljacklm

HVon: HVon.c
	$(CC) $< -o $@ -lljacklm

clean:
	rm -f list-all analog digitalIO OurDigitalIO InitializeDigitalIO easyFunctions stream Poweron Clock0 Clock1 Clock2 Clock3 CTR0 CTR1 CTR2 CTR3 SDA0 SDA1 SDA2 SDA3 HVon *.c~
