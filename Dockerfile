# Use the official GCC image from the Docker Hub
FROM gcc:latest

ENV LIBGL_ALWAYS_INDIRECT=1

# Install necessary libraries, including SDL2 and OpenGL support
RUN apt-get update && \
    apt-get install -y libsdl2-dev libgl1-mesa-dev

# Set the working directory in the container
WORKDIR /usr/src/zoot

# Copy the current directory contents into the container
COPY . .

# Compile the C++ source file with SDL2
RUN g++ -o zoot main.cpp -lSDL2 -lGL

# Command to run the executable
CMD ["./zoot"]
