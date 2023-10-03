package hlgs;

typedef CArrayFloatPtr = hl.Abstract<"hlgs_carrayfloat">

@:hlNative('hlgs')
class CArrayFloat {
  private var arr: CArrayFloatPtr;
  public var length(default, null): Int = 0;

  private static function newCarrayfloatEx(len: Int): CArrayFloatPtr { return null; }
  private static function disposeCarrayfloatEx(arr: CArrayFloatPtr): Void {}
  private static function carrayfloatSetNthEx(arr: CArrayFloatPtr, n: Int, val: Single): Void {}

  public function new(len: Int) {
    arr = newCarrayfloatEx(len);
    length = len;
  }

  public inline function dispose() {
    disposeCarrayfloatEx(arr);
  }

  public inline function setNth(n: Int, value: Single) {
    carrayfloatSetNthEx(arr, n, value);
  }

  /**
   * With great power, comes great responsibility.
   */
  public inline function getPtr(): Dynamic {
    return arr;
  }

  public static function fromArray(arr: Array<Single>): CArrayFloat {
    var ret: CArrayFloat = new CArrayFloat(arr.length);
    for (i in 0...arr.length)
      ret.setNth(i, arr[i]);
    return ret;
  }
}

