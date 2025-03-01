# Use an official GCC runtime as a parent image
FROM gcc:latest

# Install gdb
RUN apt-get update && apt-get install -y gdb

# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the C++ code
RUN g++ -g -I include -o WhoopsGameLogic src/main.cpp src/game_logic/*.cpp

# Make port 80 available to the world outside this container
EXPOSE 80

# Run the compiled binary when the container launches
CMD ["gdb","./WhoopsGameLogic"]