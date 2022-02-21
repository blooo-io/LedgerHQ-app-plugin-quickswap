module.exports = {
  env: {
    es2021: true,
    node: true,
    jest: true,
  },
  extends: ["eslint:recommended"],
  parserOptions: {
    sourceType: "module",
  },
  rules: {
    "linebreak-style": ["error", "unix"],
    semi: ["error", "always"],
  },
};
