# Protobuf Packet

This is a schema for a general purpose protofile for transmitting environment data.

Install `nanopb-generator`:

```
brew install nanopb-generator
```

Install/upgrade `google` and `protobuf`:

```
pip uninstall protobuf
pip uninstall google
pip install google 
pip install --upgrade protobuf
```

Create directories `lib/proto` and `lib/protobuf-packet`.
Create `lib/protobuf-packet/packet.proto`.
CD packet.proto
Run:
```
python /opt/homebrew/Cellar/nanopb-generator/0.4.5/bin/nanopb_generator.py --options-path . --output-dir=../proto packet.proto
```

To decode in `Node-RED`, place `packet.proto` in e.g. `data\proto` in `Node-RED`'s data directory and reference it in the `decode` node.