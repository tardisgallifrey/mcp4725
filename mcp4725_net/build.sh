#!/bin/bash

dotnet publish -r linux-arm -c release /p:PublishSingleFile=true -o /home/tardis1/bin
