package hlgs;

typedef PipelinePtr = hl.Abstract<"hlgs_pipeline">

@:hlNative('hlgs')
class Pipeline {
  private var pip: PipelinePtr;

  private static function newPipelineEx(shader: hl.Abstract<"hlgs_shader">): PipelinePtr { return null; }
  private static function disposePipelineEx(pip: PipelinePtr): Void {}

  public function new(shader: Shader) {
    pip = newPipelineEx(shader.getPtr());
  }

  public inline function dispose() {
    disposePipelineEx(pip);
  }

  /**
   * With great power, comes great responsibility.
   */
  public inline function getPtr(): Dynamic {
    return pip;
  }
}

