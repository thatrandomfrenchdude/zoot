#!/bin/bash

# Build the Docker image
docker-compose build

# Run the Docker container with automatic removal
docker-compose run --rm zoot

# Remove the Docker image
docker rmi $(docker images -q 2d_game-zoot)
