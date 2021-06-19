target:=netdevice
$(target):%:%.c
	gcc $(CFLAGS) $^ -o $@ -lcap
clean:
	-rm -rf $(target)
