package hlgs;

abstract ExtDynamic<T>(Dynamic) from T to T {}

@:hlNative('hlgs')
class Gs {
  /**
   *Only exists for internal use. DO NOT CALL IF YOU DONT KNOW WHAT YOURE DOING.
   */
  public static function createEx(app: Dynamic, title: hl.Bytes, titleLen: Int): Void {}
  public static function appIsRunning() : Bool { return false; }
  public static function frame(): Void {}
  
  public static inline function create(desc: AppDesc): Void {
    var tempApp = {
      width: desc.width,
      height: desc.height,
      fps: desc.fps,
      vsync: desc.vsync
    };
    createEx(tempApp, desc.title.toBytes(), desc.title.length);
    tempApp = null;
    desc = null;
  }
}
