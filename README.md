# Circle of Fifths

*The circle of fifths on your wrist.*

<img src="screenshots/shot_emery_classic.png" alt="shot_emery_classic.png"> <img src="screenshots/shot_emery_info.png" alt="shot_emery_info.png"> <img src="screenshots/shot_emery_short.png" alt="shot_emery_short.png"> <img src="screenshots/shot_gabbro_classic.png" alt="shot_gabbro_classic.png"> <img src="screenshots/shot_gabbro_info.png" alt="shot_gabbro_info.png"> <img src="screenshots/shot_gabbro_short.png" alt="shot_gabbro_short.png">

A Pebble watchface (v1.2.0), available in the [Rebble App Store](https://apps.repebble.com/582ac6cc8c7fff9edf000230).

An analog watchface built around the circle of fifths. The twelve major keys sit around the dial where the hour numbers would be - C at twelve, G at one, D at two and so on clockwise - and the relative minor of each key is set in red just inside it.

Neighbouring keys are a fifth apart, and each major key shares its key signature with the minor key below it. That makes the face a quick reference for transposing, finding related chords or simply learning the circle by heart while you check the time.

Two plain hands, a ring of minute marks and a white face. If you like, it also shows the battery level and today's step count.

The face redraws once a minute and does nothing in between: no second hand, no animation, no weather to fetch and no sensors beyond the step count the watch keeps anyway.

## Settings

- Circle of fourths - mirrors the dial so the flat keys sit on the right and each hour step goes up a perfect fourth: C, F, Bb, Eb and so on clockwise.
- Use shorter hands - halves the hands so they stay clear of the key names.
- Show Battery - the charge level as the watch reports it.
- Show Steps - today's step count from Pebble Health.

## Platforms

- Pebble Time 2 (`emery`)
- Pebble Round 2 (`gabbro`)
- Pebble Time Round (`chalk`)
- Pebble Time (`basalt`)
- Pebble 2 (`diorite`)
- Pebble 2 Duo (`flint`)
- Pebble / Pebble Steel (`aplite`)

## Building

With the [Pebble SDK](https://developer.repebble.com/sdk/):

```bash
pebble build
pebble install --emulator emery
```

The repository can also be imported into CloudPebble as is.

## Release notes

### 1.2.0

New setting "Circle of fourths": it mirrors the dial, so C stays at twelve but the flat keys now sit on the right. Every hour the hand moves up a perfect fourth - C, F, Bb, Eb and so on. The relative minor keys follow along.

### 1.1.1

The "Use shorter hands" setting is now remembered. Before, the hands went back to full length whenever the watchface restarted - after leaving an app, after an update or after a reboot.

### 1.1.0

Added the newer models and a settings page.

## Status

Version 1.2.0 is built and checked in the emulator on gabbro (normal and mirrored dial). It was published to the Rebble App Store on 18 Nov 2026. The store screenshots are still the ones from 1.1.1 and show the normal dial only; the mirrored dial has no screenshot yet. The project has no `screenshots/presets.json`, so `pb.ps1 shots` does not work for it until one is added.

## License

MIT License, see [LICENSE](LICENSE).
