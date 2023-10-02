package hlgs;

/**
  This class essentially just describes the application. (Similar to gs_app_desc_t.)
**/
class AppDesc {
  public var width: Int = 0;
  public var height: Int = 0;
  public var title: HString = "Hlgs App";
  public var fps: Int = 60;
  public var vsync: Bool = false;

  public function new() {}
}

