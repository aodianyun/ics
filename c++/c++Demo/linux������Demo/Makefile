test_app:
	g++ -g -o test_app test_app.cpp -L"./lib" ./lib/libadcloud_app.so  -I"./include" -Wl,-rpath,./lib 
clean:
	@rm ./test_app