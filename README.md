# Clymit

Metrics for your home atmosphere

## Project Structure

- `telemetry/node` - a **node** logs data from internal sensors, and sends it to a **master** server
- `telemetry/master` - the **master** receives data from **nodes**, and logs it to a database
- `server/` - the API **server** gives client access to the database
- `web/` - web application / interface for analyzing and interacting with data
