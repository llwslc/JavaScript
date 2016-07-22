{
  "targets": [
    {
      "target_name": "testAddons",
      "sources": [ "cTestAddons.cc" ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
        "conditions": [
            ['OS=="mac"', { 'xcode_settings': { 'GCC_ENABLE_CPP_EXCEPTIONS': 'YES' } }],
            ['OS=="win"', { "defines": ["NOMINMAX"] }],
        ],
    }
  ]
}