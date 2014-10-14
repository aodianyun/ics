#!/bin/bash

nohup node start.js  > ./'nohup_'$1`date +%y-%m-%d_%H%M%S`'.out' 2>&1 &



