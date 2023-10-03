package hlgs;

typedef CommandBufferPtr = hl.Abstract<"hlgs_cb">

@:hlNative('hlgs')
class CommandBuffer {
  private var cb: CommandBufferPtr = null;

  private static function newCommandBufferEx(): CommandBufferPtr { return null; }
  private static function disposeCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  private static function submitCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  private static function beginRenderpassCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  private static function endRenderpassCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  private static function clearCommandBufferEx(cbptr: CommandBufferPtr, r: Single, g: Single, b: Single): Void {}
  private static function drawCommandBufferEx(cbptr: CommandBufferPtr, begin: Int, end: Int): Void {}
  private static function bindPipelineEx(pip: hl.Abstract<"hlgs_pipeline">, cb: CommandBufferPtr): Void {}
  private static function applyVboCommandBufferEx(cbptr: CommandBufferPtr, vbo: hl.Abstract<"hlgs_vbo">) {}
  
  public function new() {
    this.cb = newCommandBufferEx();
  }

  public inline function dispose() {
    disposeCommandBufferEx(this.cb);
  }

  public inline function submit() {
    submitCommandBufferEx(this.cb);
  }

  public inline function renderpassBegin() {
    beginRenderpassCommandBufferEx(this.cb);
  }

  public inline function renderpassEnd() {
    endRenderpassCommandBufferEx(this.cb);
  }

  public inline function clear(r: Single, g: Single, b: Single) {
    clearCommandBufferEx(this.cb, r, g, b);
  }

  public inline function draw(begin: Int, end: Int) {
    drawCommandBufferEx(cb, begin, end);
  }

  public inline function bindPipeline(pip: Pipeline) {
    bindPipelineEx(pip.getPtr(), cb);
  }

  public inline function applyVbo(vbo: VertexBuffer) {
    applyVboCommandBufferEx(cb, vbo.getPtr());
  }
}

