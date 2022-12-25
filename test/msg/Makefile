bin:= server client

all:$(bin)
server:%:%.c
	$(CC) $^ -o $@
client:%:%.c
	$(CC) $^ -o $@
clean:
	-rm -rf $(bin)
.PHONY:
	clean
