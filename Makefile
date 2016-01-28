all:
	g++ assignment1.cpp -o assignment1
	g++ driver.cpp -o driver;
clean:
	rm Outputs/*;
	rm assignment*;
	rm driver;
