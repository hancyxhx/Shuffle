all :
	make -C src
	mkdir -p output
	mv src/shuffle output/

clean :
	rm -rf output/*
