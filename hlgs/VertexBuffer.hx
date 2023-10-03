package hlgs;

typedef VertexBufferPtr = hl.Abstract<"hlgs_vbo">

@:hlNative('hlgs')
class VertexBuffer {
  var vbo: VertexBufferPtr;

  public static function newVboEx(data: hl.Bytes, len: Int): VertexBufferPtr { return null; }

  public function new(d: Array<Single>) {
    var v_bytes: hl.Bytes = hl.Bytes.fromValue(d[0], d.length * 4);
    vbo = newVboEx(v_bytes, d.length);
  }
}

