package hlgs;

typedef ShaderPtr = hl.Abstract<"hlgs_shader">

@:hlNative('hlgs')
class Shader {
  private var shader: ShaderPtr;

  private static function newShaderEx(vSrc: hl.Bytes, vLen: Int, fSrc: hl.Bytes, fLen: Int, name: hl.Bytes, nameLen: Int): ShaderPtr { return null; }
  private static function disposeShaderEx(shader: ShaderPtr): Void {}

  public function new(vertexShader: String, fragmentShader: String, name: String) {
    shader = newShaderEx(
      cast (vertexShader, HString).toBytes(), vertexShader.length,
      cast (fragmentShader, HString).toBytes(), fragmentShader.length,
      cast (name, HString).toBytes(), name.length
    );
  }

  public function dispose() {
    disposeShaderEx(shader);
  }

  /**
   * With great power, comes great responsibility.
   */
  public inline function getPtr(): Dynamic {
    return shader;
  }
}

