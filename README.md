# Trac Syntax Shrekifier
So, you're all comfy in your Trac Wiki swamp, but you realize that you have no
one to share it with.  You soon come to find out that no one likes your stinky,
slimy swamp, but what do you do?  Never fear, the Shrektastic scripts from Far
Far Away are here to save the day!

## Swamp Essentials
In order to have a Shrektastic experience, you'll need to have the following
programs installed on your computer:

  * Git
  * A recent version of Bash
  * GNU `sed` (or something close)
  * Something sane as your `cc`
  * `dos2unix`
  * GNU `make`

You'll also need to make sure that you have your `user.name` and `user.email`
settings squared away with [git-config(1)](https://git-scm.com/docs/git-config).

## Unleashing Your Inner Ogre
First, build the `blockifiers`:
```
make blockifiers
```

Edit `quick-n-dirty` to specify your Trac Wiki inputs in `files( ... )`
and your `outdir`:
```
vi quick-n-dirty
```

Point to an input directory, and away you go (using `../LinuxPMI.wiki` as an
example):
```
./quick-n-dirty ../LinuxPMI.wiki
```

## Previewing Your Work
Install the Gollum Ruby Gem to get a GitLab-like Wiki experience:
```
gem install gollum
```

`cd` to your `$outdir` and run:
```
make test
```

Go to [127.0.0.1:4567](http://127.0.0.1:4567) in a browser to preview your wiki!

> <h3>⚠  Shrek Tips: </h3>
>
>  - If `make test` doesn't work, you may need to add your Ruby Gems to your
>    `$PATH`.  On most GNU/Linux systems, this can be accomplished by adding
>    something a line like `PATH="$HOME/.gem/ruby/3.0.0/bin:$PATH"` to your
>    profile.
>
>  - If your wiki's landing page doesn't work in the browser, try changing
>    the value in `$outdir`'s `config.rb` file!
