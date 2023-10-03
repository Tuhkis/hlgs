package hlgs;


typedef CArrayFloatPtr = hl.Abstract<"hlgs_carrayfloat">

@:hlNative('hlgs')
class CArrayFloat {
  private var arr: CArrayFloatPtr;

  private static function newCarrayfloatEx(len: Int): CArrayFloatPtr { return null; }
  private static function disposeCarrayfloatEx(arr: CArrayFloatPtr): Void {}
  private static function carrayfloatSetNthEx(arr: CArrayFloatPtr, n: Int, val: Single): Void {}

  public function new(len: Int) {
    arr = newCarrayfloatEx(len);
  }

  public function dispose() {
    disposeCarrayfloatEx(arr);
  }
}

