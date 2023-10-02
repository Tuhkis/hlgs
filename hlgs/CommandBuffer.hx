package hlgs;

typedef CommandBufferPtr = hl.Abstract<"hlgs_cb">

@:hlNative('hlgs')
class CommandBuffer {
  private var cb: CommandBufferPtr = null;

  public static function newCommandBufferEx(): CommandBufferPtr { return null; }
  public static function disposeCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  public static function submitCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  public static function beginRenderpassCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  public static function endRenderpassCommandBufferEx(cbptr: CommandBufferPtr): Void {}
  public static function clearCommandBufferEx(cbptr: CommandBufferPtr, r: Single, g: Single, b: Single): Void {}
  
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
}

