package hlgs;

@:access(String)
@:forward
abstract HString(String) from String to String {
  @:to public inline function toBytes(): hl.Bytes {
    return switch this {
      case null: null;
      default: this.bytes;
    }
  }
}

