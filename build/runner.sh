#!/bin/bash

qemu-system-arm -m 512 -M raspi2 -serial stdio -kernel kernel.elf
