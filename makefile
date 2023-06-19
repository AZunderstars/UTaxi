CC := g++ -std=c++11 
COMPILE_FLAG = -c 
BUILD += build
SRC += src

all: $(BUILD)/utaxi.out

$(BUILD)/utaxi.out: $(BUILD)/main.o $(BUILD)/Utaxi.o $(BUILD)/Region.o $(BUILD)/Passenger.o $(BUILD)/User.o $(BUILD)/Driver.o $(BUILD)/Trip.o
	$(CC) $(BUILD)/main.o $(BUILD)/Utaxi.o $(BUILD)/Region.o $(BUILD)/Passenger.o $(BUILD)/User.o $(BUILD)/Driver.o $(BUILD)/Trip.o -o utaxi.out

$(BUILD)/main.o: $(SRC)/main.cpp $(SRC)/Utaxi.cpp $(SRC)/Utaxi.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/Utaxi.o: $(SRC)/Utaxi.cpp $(SRC)/Utaxi.hpp $(SRC)/Region.cpp $(SRC)/Region.hpp $(SRC)/Passenger.cpp $(SRC)/Passenger.hpp $(SRC)/User.cpp $(SRC)/User.hpp $(SRC)/Driver.cpp $(SRC)/Driver.hpp $(SRC)/Trip.cpp $(SRC)/Trip.hpp $(SRC)/consts.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/Utaxi.cpp -o $(BUILD)/Utaxi.o

$(BUILD)/Region.o: $(SRC)/Region.cpp $(SRC)/Region.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/Region.cpp -o $(BUILD)/Region.o

$(BUILD)/Passenger.o: $(SRC)/Passenger.cpp $(SRC)/Passenger.hpp $(SRC)/User.cpp $(SRC)/User.hpp $(SRC)/consts.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/Passenger.cpp -o $(BUILD)/Passenger.o

$(BUILD)/User.o: $(SRC)/User.cpp $(SRC)/User.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/User.cpp -o $(BUILD)/User.o

$(BUILD)/Driver.o: $(SRC)/Driver.cpp $(SRC)/Driver.hpp $(SRC)/User.cpp $(SRC)/User.hpp $(SRC)/consts.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/Driver.cpp -o $(BUILD)/Driver.o

$(BUILD)/Trip.o: $(SRC)/Trip.cpp $(SRC)/Trip.hpp $(SRC)/Driver.cpp $(SRC)/Driver.hpp $(SRC)/Passenger.cpp $(SRC)/Passenger.hpp $(SRC)/consts.hpp
	$(CC) $(COMPILE_FLAG) $(SRC)/Trip.cpp -o $(BUILD)/Trip.o

clean:
	rm $(BUILD)/*.o
