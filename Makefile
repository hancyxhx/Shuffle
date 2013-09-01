all :
	make -C src
	mkdir -p output/bin/
	cp src/shuffle output/bin/

clean :
	make -C src clean
	rm -rf output/
