#!/bin/bash

dotnet publish -r linux-arm -c release --self-contained true /p:PublishSingleFile=true -o /home/tardis1/bin

