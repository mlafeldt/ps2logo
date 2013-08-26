GO = go

ifeq ("$(origin X)", "command line")
  GOFLAGS = -x
endif

all: build

get:
	$(GO) get -d $(GOFLAGS) ./...

build: get
	$(GO) build $(GOFLAGS) ./...

install: get
	$(GO) install $(GOFLAGS) ./...

test_dep: get
	$(GO) test -i $(GOFLAGS) ./...

test: test_dep
	$(GO) test -v $(GOFLAGS) ./...

clean:
	$(GO) clean $(GOFLAGS) ./...

.PHONY: all get build install test_dep test clean
