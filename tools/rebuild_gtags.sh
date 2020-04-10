#!/bin/sh
pwd=$(sh pwd);
echo $(pwd);
cd $(pwd);
rm -rf GRTAGS;
rm -rf GTAGS;
rm -rf GPATH;
gtags;
