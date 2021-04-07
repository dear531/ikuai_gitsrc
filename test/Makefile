target	:=uname
CFLAGS	+=-D_GNU_SOURCE
$(target):%:%.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf $(target)
