#!/usr/bin/env python3
# coding: utf-8

import licant
import licant.install
import os
import sys

licant.cxx_static_and_shared(
    sources=["mosquitto_client/mqtt.cpp"],
    include_paths=["."],
    name="libraries",
    static_lib="libmosquitto_client.a",
    shared_lib="libmosquitto_client.so",
    libs=["mosquittopp"],
    cxx_flags="-fPIC",
    cxxstd="c++17",
    ccstd="c11",
    optimize="-O3"
)

licant.install.install_library(
    tgt="install",
    uninstall="uninstall",
    libtgt=["libmosquitto_client.so", "libmosquitto_client.a"],
    hroot="mosquitto_client",
    headers="mosquitto_client")

licant.fileset("all", targets=["libmosquitto_client.so", "libmosquitto_client.a"])

licant.ex("all")
