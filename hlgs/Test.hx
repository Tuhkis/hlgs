package;

class Test {
  public static function main() {
    var app = {
      width : 1024,
      height : 800,
      title : 'GS Window from Haxe'
    };

    hlgs.Gs.create(app);
    while (hlgs.Gs.appIsRunning()) {
      hlgs.Gs.frame();
    }
    trace('success!!');
  }
}
