package hlgs;

typedef VertexBufferPtr = hl.Abstract<"hlgs_vbo">

@:hlNative('hlgs')
class VertexBuffer {
  var vbo: VertexBufferPtr;

  private static function newVboEx(data: hl.Abstract<"hlgs_carrayfloat">): VertexBufferPtr { return null; }
  private static function disposeVboEx(vbo: VertexBufferPtr): Void {}

  public function new(d: CArrayFloat) {
    vbo = newVboEx(d.getPtr());
  }

  public inline function dispose() {
    disposeVboEx(vbo);
  }

  public static function fromArray(arr: Array<Single>): VertexBuffer {
    var carr: CArrayFloat = CArrayFloat.fromArray(arr);
    var ret = new VertexBuffer(carr);
    carr.dispose();
    return ret;
  }

  /**
   * With great power, comes great responsibility.
   */
  public inline function getPtr(): Dynamic {
    return vbo;
  }
}

