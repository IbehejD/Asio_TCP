### Dev stage ###
FROM ubuntu:24.04 AS dev

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    g++ \
    make \
    gdb \
    git \
    ninja-build \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/* \
    && update-ca-certificates \
    && python3 -m pip install conan --break-system-packages

WORKDIR /workspaces/EventDispatcher

### Build stage ###
FROM dev AS build

WORKDIR /app

COPY CMakeLists.txt ./
COPY include ./include
COPY src ./src
COPY tests ./tests

RUN cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON \
    && cmake --build build -j$(nproc)

### Test stage ###
FROM build AS test

WORKDIR /app

RUN ctest --test-dir build --output-on-failure

### Runtime stage ###
FROM ubuntu:24.04 AS runtime

RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=build /app/build/event_dispatcher_app ./event_dispatcher_app

CMD ["./event_dispatcher_app"]
