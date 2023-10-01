package hlgs;

abstract ExtDynamic<T>(Dynamic) from T to T {}

typedef App = {
    width : Int,
    height : Int,
    title : String
}

@:hlNative('hlgs')
class Gs {
  public static function create(app: Dynamic) {}
  public static function appIsRunning() : Bool { return false; }
  public static function frame() {}
}
