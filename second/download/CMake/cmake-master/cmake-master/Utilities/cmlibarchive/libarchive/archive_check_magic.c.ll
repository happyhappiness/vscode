; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_check_magic.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque

@.str = private unnamed_addr constant [28 x i8] c"PROGRAMMER ERROR: Function \00", align 1
@.str.1 = private unnamed_addr constant [39 x i8] c" invoked with invalid archive handle.\0A\00", align 1
@.str.2 = private unnamed_addr constant [88 x i8] c"PROGRAMMER ERROR: Function '%s' invoked on '%s' archive object, which is not supported.\00", align 1
@.str.3 = private unnamed_addr constant [100 x i8] c"INTERNAL ERROR: Function '%s' invoked with archive structure in state '%s', should be in state '%s'\00", align 1
@.str.4 = private unnamed_addr constant [14 x i8] c"archive_write\00", align 1
@.str.5 = private unnamed_addr constant [13 x i8] c"archive_read\00", align 1
@.str.6 = private unnamed_addr constant [19 x i8] c"archive_write_disk\00", align 1
@.str.7 = private unnamed_addr constant [18 x i8] c"archive_read_disk\00", align 1
@.str.8 = private unnamed_addr constant [14 x i8] c"archive_match\00", align 1
@.str.9 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"new\00", align 1
@.str.11 = private unnamed_addr constant [7 x i8] c"header\00", align 1
@.str.12 = private unnamed_addr constant [5 x i8] c"data\00", align 1
@.str.13 = private unnamed_addr constant [4 x i8] c"eof\00", align 1
@.str.14 = private unnamed_addr constant [7 x i8] c"closed\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"fatal\00", align 1
@.str.16 = private unnamed_addr constant [3 x i8] c"??\00", align 1

; Function Attrs: nounwind uwtable
define i32 @__archive_check_magic(%struct.archive* %a, i32 %magic, i32 %state, i8* %function) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %magic.addr = alloca i32, align 4
  %state.addr = alloca i32, align 4
  %function.addr = alloca i8*, align 8
  %states1 = alloca [64 x i8], align 16
  %states2 = alloca [64 x i8], align 16
  %handle_type = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !124, metadata !125), !dbg !126
  store i32 %magic, i32* %magic.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %magic.addr, metadata !127, metadata !125), !dbg !128
  store i32 %state, i32* %state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %state.addr, metadata !129, metadata !125), !dbg !130
  store i8* %function, i8** %function.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %function.addr, metadata !131, metadata !125), !dbg !132
  call void @llvm.dbg.declare(metadata [64 x i8]* %states1, metadata !133, metadata !125), !dbg !137
  call void @llvm.dbg.declare(metadata [64 x i8]* %states2, metadata !138, metadata !125), !dbg !139
  call void @llvm.dbg.declare(metadata i8** %handle_type, metadata !140, metadata !125), !dbg !141
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !142
  %magic1 = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 0, !dbg !143
  %1 = load i32, i32* %magic1, align 8, !dbg !143
  %call = call i8* @archive_handle_type_name(i32 %1), !dbg !144
  store i8* %call, i8** %handle_type, align 8, !dbg !145
  %2 = load i8*, i8** %handle_type, align 8, !dbg !146
  %tobool = icmp ne i8* %2, null, !dbg !146
  br i1 %tobool, label %if.end, label %if.then, !dbg !148

if.then:                                          ; preds = %entry
  call void @errmsg(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0)), !dbg !149
  %3 = load i8*, i8** %function.addr, align 8, !dbg !151
  call void @errmsg(i8* %3), !dbg !152
  call void @errmsg(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.1, i32 0, i32 0)), !dbg !153
  call void @diediedie(), !dbg !154
  br label %if.end, !dbg !155

if.end:                                           ; preds = %if.then, %entry
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !156
  %magic2 = getelementptr inbounds %struct.archive, %struct.archive* %4, i32 0, i32 0, !dbg !158
  %5 = load i32, i32* %magic2, align 8, !dbg !158
  %6 = load i32, i32* %magic.addr, align 4, !dbg !159
  %cmp = icmp ne i32 %5, %6, !dbg !160
  br i1 %cmp, label %if.then3, label %if.end5, !dbg !161

if.then3:                                         ; preds = %if.end
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !162
  %8 = load i8*, i8** %function.addr, align 8, !dbg !164
  %9 = load i8*, i8** %handle_type, align 8, !dbg !165
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %7, i32 -1, i8* getelementptr inbounds ([88 x i8], [88 x i8]* @.str.2, i32 0, i32 0), i8* %8, i8* %9), !dbg !166
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !167
  %state4 = getelementptr inbounds %struct.archive, %struct.archive* %10, i32 0, i32 1, !dbg !168
  store i32 32768, i32* %state4, align 4, !dbg !169
  store i32 -30, i32* %retval, align 4, !dbg !170
  br label %return, !dbg !170

if.end5:                                          ; preds = %if.end
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !171
  %state6 = getelementptr inbounds %struct.archive, %struct.archive* %11, i32 0, i32 1, !dbg !173
  %12 = load i32, i32* %state6, align 4, !dbg !173
  %13 = load i32, i32* %state.addr, align 4, !dbg !174
  %and = and i32 %12, %13, !dbg !175
  %cmp7 = icmp eq i32 %and, 0, !dbg !176
  br i1 %cmp7, label %if.then8, label %if.end18, !dbg !177

if.then8:                                         ; preds = %if.end5
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !178
  %state9 = getelementptr inbounds %struct.archive, %struct.archive* %14, i32 0, i32 1, !dbg !181
  %15 = load i32, i32* %state9, align 4, !dbg !181
  %cmp10 = icmp ne i32 %15, 32768, !dbg !182
  br i1 %cmp10, label %if.then11, label %if.end16, !dbg !183

if.then11:                                        ; preds = %if.then8
  %16 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !184
  %17 = load i8*, i8** %function.addr, align 8, !dbg !185
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %states1, i32 0, i32 0, !dbg !186
  %18 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !187
  %state12 = getelementptr inbounds %struct.archive, %struct.archive* %18, i32 0, i32 1, !dbg !188
  %19 = load i32, i32* %state12, align 4, !dbg !188
  %call13 = call i8* @write_all_states(i8* %arraydecay, i32 %19), !dbg !189
  %arraydecay14 = getelementptr inbounds [64 x i8], [64 x i8]* %states2, i32 0, i32 0, !dbg !190
  %20 = load i32, i32* %state.addr, align 4, !dbg !191
  %call15 = call i8* @write_all_states(i8* %arraydecay14, i32 %20), !dbg !192
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %16, i32 -1, i8* getelementptr inbounds ([100 x i8], [100 x i8]* @.str.3, i32 0, i32 0), i8* %17, i8* %call13, i8* %call15), !dbg !193
  br label %if.end16, !dbg !193

if.end16:                                         ; preds = %if.then11, %if.then8
  %21 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !194
  %state17 = getelementptr inbounds %struct.archive, %struct.archive* %21, i32 0, i32 1, !dbg !195
  store i32 32768, i32* %state17, align 4, !dbg !196
  store i32 -30, i32* %retval, align 4, !dbg !197
  br label %return, !dbg !197

if.end18:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !198
  br label %return, !dbg !198

return:                                           ; preds = %if.end18, %if.end16, %if.then3
  %22 = load i32, i32* %retval, align 4, !dbg !199
  ret i32 %22, !dbg !199
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i8* @archive_handle_type_name(i32 %m) #0 !dbg !108 {
entry:
  %retval = alloca i8*, align 8
  %m.addr = alloca i32, align 4
  store i32 %m, i32* %m.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %m.addr, metadata !200, metadata !125), !dbg !201
  %0 = load i32, i32* %m.addr, align 4, !dbg !202
  switch i32 %0, label %sw.default [
    i32 -1329217314, label %sw.bb
    i32 14594245, label %sw.bb1
    i32 -1073631035, label %sw.bb2
    i32 195932357, label %sw.bb3
    i32 212668873, label %sw.bb4
  ], !dbg !203

sw.bb:                                            ; preds = %entry
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.4, i32 0, i32 0), i8** %retval, align 8, !dbg !204
  br label %return, !dbg !204

sw.bb1:                                           ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.5, i32 0, i32 0), i8** %retval, align 8, !dbg !206
  br label %return, !dbg !206

sw.bb2:                                           ; preds = %entry
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.6, i32 0, i32 0), i8** %retval, align 8, !dbg !207
  br label %return, !dbg !207

sw.bb3:                                           ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.7, i32 0, i32 0), i8** %retval, align 8, !dbg !208
  br label %return, !dbg !208

sw.bb4:                                           ; preds = %entry
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.8, i32 0, i32 0), i8** %retval, align 8, !dbg !209
  br label %return, !dbg !209

sw.default:                                       ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !210
  br label %return, !dbg !210

return:                                           ; preds = %sw.default, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %1 = load i8*, i8** %retval, align 8, !dbg !211
  ret i8* %1, !dbg !211
}

; Function Attrs: nounwind uwtable
define internal void @errmsg(i8* %m) #0 !dbg !111 {
entry:
  %m.addr = alloca i8*, align 8
  %s = alloca i64, align 8
  %written = alloca i64, align 8
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !212, metadata !125), !dbg !213
  call void @llvm.dbg.declare(metadata i64* %s, metadata !214, metadata !125), !dbg !215
  %0 = load i8*, i8** %m.addr, align 8, !dbg !216
  %call = call i64 @strlen(i8* %0) #6, !dbg !217
  store i64 %call, i64* %s, align 8, !dbg !215
  call void @llvm.dbg.declare(metadata i64* %written, metadata !218, metadata !125), !dbg !219
  br label %while.cond, !dbg !220

while.cond:                                       ; preds = %if.end, %entry
  %1 = load i64, i64* %s, align 8, !dbg !221
  %cmp = icmp ugt i64 %1, 0, !dbg !223
  br i1 %cmp, label %while.body, label %while.end, !dbg !224

while.body:                                       ; preds = %while.cond
  %2 = load i8*, i8** %m.addr, align 8, !dbg !225
  %3 = load i8*, i8** %m.addr, align 8, !dbg !227
  %call1 = call i64 @strlen(i8* %3) #6, !dbg !228
  %call2 = call i64 @write(i32 2, i8* %2, i64 %call1), !dbg !229
  store i64 %call2, i64* %written, align 8, !dbg !231
  %4 = load i64, i64* %written, align 8, !dbg !232
  %cmp3 = icmp sle i64 %4, 0, !dbg !234
  br i1 %cmp3, label %if.then, label %if.end, !dbg !235

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !236

if.end:                                           ; preds = %while.body
  %5 = load i64, i64* %written, align 8, !dbg !237
  %6 = load i8*, i8** %m.addr, align 8, !dbg !238
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %5, !dbg !238
  store i8* %add.ptr, i8** %m.addr, align 8, !dbg !238
  %7 = load i64, i64* %written, align 8, !dbg !239
  %8 = load i64, i64* %s, align 8, !dbg !240
  %sub = sub i64 %8, %7, !dbg !240
  store i64 %sub, i64* %s, align 8, !dbg !240
  br label %while.cond, !dbg !241

while.end:                                        ; preds = %if.then, %while.cond
  ret void, !dbg !243
}

; Function Attrs: nounwind uwtable
define internal void @diediedie() #0 !dbg !114 {
entry:
  call void @abort() #7, !dbg !244
  unreachable, !dbg !244

return:                                           ; No predecessors!
  ret void, !dbg !245
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i8* @write_all_states(i8* %buff, i32 %states) #0 !dbg !117 {
entry:
  %buff.addr = alloca i8*, align 8
  %states.addr = alloca i32, align 4
  %lowbit = alloca i32, align 4
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !246, metadata !125), !dbg !247
  store i32 %states, i32* %states.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %states.addr, metadata !248, metadata !125), !dbg !249
  call void @llvm.dbg.declare(metadata i32* %lowbit, metadata !250, metadata !125), !dbg !251
  %0 = load i8*, i8** %buff.addr, align 8, !dbg !252
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !252
  store i8 0, i8* %arrayidx, align 1, !dbg !253
  br label %while.cond, !dbg !254

while.cond:                                       ; preds = %if.end, %entry
  %1 = load i32, i32* %states.addr, align 4, !dbg !255
  %2 = load i32, i32* %states.addr, align 4, !dbg !257
  %neg = xor i32 %2, -1, !dbg !258
  %add = add i32 1, %neg, !dbg !259
  %and = and i32 %1, %add, !dbg !260
  store i32 %and, i32* %lowbit, align 4, !dbg !261
  %cmp = icmp ne i32 %and, 0, !dbg !262
  br i1 %cmp, label %while.body, label %while.end, !dbg !263

while.body:                                       ; preds = %while.cond
  %3 = load i32, i32* %lowbit, align 4, !dbg !264
  %neg1 = xor i32 %3, -1, !dbg !266
  %4 = load i32, i32* %states.addr, align 4, !dbg !267
  %and2 = and i32 %4, %neg1, !dbg !267
  store i32 %and2, i32* %states.addr, align 4, !dbg !267
  %5 = load i8*, i8** %buff.addr, align 8, !dbg !268
  %6 = load i32, i32* %lowbit, align 4, !dbg !269
  %call = call i8* @state_name(i32 %6), !dbg !270
  %call3 = call i8* @strcat(i8* %5, i8* %call) #8, !dbg !271
  %7 = load i32, i32* %states.addr, align 4, !dbg !273
  %cmp4 = icmp ne i32 %7, 0, !dbg !275
  br i1 %cmp4, label %if.then, label %if.end, !dbg !276

if.then:                                          ; preds = %while.body
  %8 = load i8*, i8** %buff.addr, align 8, !dbg !277
  %call5 = call i8* @strcat(i8* %8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i32 0, i32 0)) #8, !dbg !278
  br label %if.end, !dbg !278

if.end:                                           ; preds = %if.then, %while.body
  br label %while.cond, !dbg !279

while.end:                                        ; preds = %while.cond
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !281
  ret i8* %9, !dbg !282
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

declare i64 @write(i32, i8*, i64) #2

; Function Attrs: noreturn nounwind
declare void @abort() #4

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8*) #5

; Function Attrs: nounwind uwtable
define internal i8* @state_name(i32 %s) #0 !dbg !120 {
entry:
  %retval = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !283, metadata !125), !dbg !284
  %0 = load i32, i32* %s.addr, align 4, !dbg !285
  switch i32 %0, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb1
    i32 4, label %sw.bb2
    i32 16, label %sw.bb3
    i32 32, label %sw.bb4
    i32 32768, label %sw.bb5
  ], !dbg !286

sw.bb:                                            ; preds = %entry
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i32 0, i32 0), i8** %retval, align 8, !dbg !287
  br label %return, !dbg !287

sw.bb1:                                           ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.11, i32 0, i32 0), i8** %retval, align 8, !dbg !289
  br label %return, !dbg !289

sw.bb2:                                           ; preds = %entry
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.12, i32 0, i32 0), i8** %retval, align 8, !dbg !290
  br label %return, !dbg !290

sw.bb3:                                           ; preds = %entry
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.13, i32 0, i32 0), i8** %retval, align 8, !dbg !291
  br label %return, !dbg !291

sw.bb4:                                           ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.14, i32 0, i32 0), i8** %retval, align 8, !dbg !292
  br label %return, !dbg !292

sw.bb5:                                           ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i32 0, i32 0), i8** %retval, align 8, !dbg !293
  br label %return, !dbg !293

sw.default:                                       ; preds = %entry
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.16, i32 0, i32 0), i8** %retval, align 8, !dbg !294
  br label %return, !dbg !294

return:                                           ; preds = %sw.default, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %1 = load i8*, i8** %retval, align 8, !dbg !295
  ret i8* %1, !dbg !295
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!121, !122}
!llvm.ident = !{!123}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_check_magic.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !108, !111, !114, !117, !120}
!4 = distinct !DISubprogram(name: "__archive_check_magic", scope: !1, file: !1, line: 130, type: !5, isLocal: false, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !13, !13, !78}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !81, !82, !83, !84, !85, !86, !87, !88, !96, !97, !98, !99, !102, !103, !104, !105, !106, !107}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !23, !24, !31, !32, !46, !52, !57, !58, !65, !66, !70, !74}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!7, !8}
!23 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !25, size: 64, align: 64, offset: 128)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DISubroutineType(types: !27)
!27 = !{!7, !8, !28}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !30, line: 180, flags: DIFlagFwdDecl)
!30 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !33, size: 64, align: 64, offset: 256)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DISubroutineType(types: !35)
!35 = !{!36, !8, !41, !43}
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !37, line: 109, baseType: !38)
!37 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !39, line: 172, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !44, line: 62, baseType: !45)
!44 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !47, size: 64, align: 64, offset: 320)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DISubroutineType(types: !49)
!49 = !{!36, !8, !41, !43, !50}
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !51, line: 40, baseType: !40)
!51 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!52 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !53, size: 64, align: 64, offset: 384)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DISubroutineType(types: !55)
!55 = !{!7, !8, !56}
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !25, size: 64, align: 64, offset: 448)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !59, size: 64, align: 64, offset: 512)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!7, !8, !62, !63, !64}
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !67, size: 64, align: 64, offset: 640)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!50, !8, !7}
!70 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !71, size: 64, align: 64, offset: 704)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64, align: 64)
!72 = !DISubroutineType(types: !73)
!73 = !{!7, !8, !7}
!74 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !75, size: 64, align: 64, offset: 768)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DISubroutineType(types: !77)
!77 = !{!78, !8, !7}
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !80)
!80 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !7, size: 32, align: 32, offset: 128)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !78, size: 64, align: 64, offset: 192)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !7, size: 32, align: 32, offset: 256)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !78, size: 64, align: 64, offset: 320)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !7, size: 32, align: 32, offset: 384)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !7, size: 32, align: 32, offset: 416)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !78, size: 64, align: 64, offset: 448)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !89, size: 192, align: 64, offset: 512)
!89 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !90, line: 58, size: 192, align: 64, elements: !91)
!90 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!91 = !{!92, !94, !95}
!92 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !89, file: !90, line: 59, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !89, file: !90, line: 60, baseType: !43, size: 64, align: 64, offset: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !89, file: !90, line: 61, baseType: !43, size: 64, align: 64, offset: 128)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !93, size: 64, align: 64, offset: 704)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !100, size: 64, align: 64, offset: 832)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !90, line: 70, flags: DIFlagFwdDecl)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !78, size: 64, align: 64, offset: 896)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !50, size: 64, align: 64, offset: 960)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !50, size: 64, align: 64, offset: 1024)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !43, size: 64, align: 64, offset: 1088)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !80, size: 8, align: 8, offset: 1152)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !43, size: 64, align: 64, offset: 1216)
!108 = distinct !DISubprogram(name: "archive_handle_type_name", scope: !1, file: !1, line: 90, type: !109, isLocal: true, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!109 = !DISubroutineType(types: !110)
!110 = !{!78, !13}
!111 = distinct !DISubprogram(name: "errmsg", scope: !1, file: !1, line: 51, type: !112, isLocal: true, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!112 = !DISubroutineType(types: !113)
!113 = !{null, !78}
!114 = distinct !DISubprogram(name: "diediedie", scope: !1, file: !1, line: 66, type: !115, isLocal: true, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!115 = !DISubroutineType(types: !116)
!116 = !{null}
!117 = distinct !DISubprogram(name: "write_all_states", scope: !1, file: !1, line: 104, type: !118, isLocal: true, isDefinition: true, scopeLine: 105, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!118 = !DISubroutineType(types: !119)
!119 = !{!93, !93, !13}
!120 = distinct !DISubprogram(name: "state_name", scope: !1, file: !1, line: 76, type: !109, isLocal: true, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!121 = !{i32 2, !"Dwarf Version", i32 4}
!122 = !{i32 2, !"Debug Info Version", i32 3}
!123 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!124 = !DILocalVariable(name: "a", arg: 1, scope: !4, file: !1, line: 130, type: !8)
!125 = !DIExpression()
!126 = !DILocation(line: 130, column: 39, scope: !4)
!127 = !DILocalVariable(name: "magic", arg: 2, scope: !4, file: !1, line: 130, type: !13)
!128 = !DILocation(line: 130, column: 55, scope: !4)
!129 = !DILocalVariable(name: "state", arg: 3, scope: !4, file: !1, line: 131, type: !13)
!130 = !DILocation(line: 131, column: 18, scope: !4)
!131 = !DILocalVariable(name: "function", arg: 4, scope: !4, file: !1, line: 131, type: !78)
!132 = !DILocation(line: 131, column: 37, scope: !4)
!133 = !DILocalVariable(name: "states1", scope: !4, file: !1, line: 133, type: !134)
!134 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 512, align: 8, elements: !135)
!135 = !{!136}
!136 = !DISubrange(count: 64)
!137 = !DILocation(line: 133, column: 7, scope: !4)
!138 = !DILocalVariable(name: "states2", scope: !4, file: !1, line: 134, type: !134)
!139 = !DILocation(line: 134, column: 7, scope: !4)
!140 = !DILocalVariable(name: "handle_type", scope: !4, file: !1, line: 135, type: !78)
!141 = !DILocation(line: 135, column: 14, scope: !4)
!142 = !DILocation(line: 142, column: 41, scope: !4)
!143 = !DILocation(line: 142, column: 44, scope: !4)
!144 = !DILocation(line: 142, column: 16, scope: !4)
!145 = !DILocation(line: 142, column: 14, scope: !4)
!146 = !DILocation(line: 144, column: 7, scope: !147)
!147 = distinct !DILexicalBlock(scope: !4, file: !1, line: 144, column: 6)
!148 = !DILocation(line: 144, column: 6, scope: !4)
!149 = !DILocation(line: 145, column: 3, scope: !150)
!150 = distinct !DILexicalBlock(scope: !147, file: !1, line: 144, column: 20)
!151 = !DILocation(line: 146, column: 10, scope: !150)
!152 = !DILocation(line: 146, column: 3, scope: !150)
!153 = !DILocation(line: 147, column: 3, scope: !150)
!154 = !DILocation(line: 148, column: 3, scope: !150)
!155 = !DILocation(line: 149, column: 2, scope: !150)
!156 = !DILocation(line: 151, column: 6, scope: !157)
!157 = distinct !DILexicalBlock(scope: !4, file: !1, line: 151, column: 6)
!158 = !DILocation(line: 151, column: 9, scope: !157)
!159 = !DILocation(line: 151, column: 18, scope: !157)
!160 = !DILocation(line: 151, column: 15, scope: !157)
!161 = !DILocation(line: 151, column: 6, scope: !4)
!162 = !DILocation(line: 152, column: 21, scope: !163)
!163 = distinct !DILexicalBlock(scope: !157, file: !1, line: 151, column: 25)
!164 = !DILocation(line: 155, column: 7, scope: !163)
!165 = !DILocation(line: 156, column: 7, scope: !163)
!166 = !DILocation(line: 152, column: 3, scope: !163)
!167 = !DILocation(line: 157, column: 3, scope: !163)
!168 = !DILocation(line: 157, column: 6, scope: !163)
!169 = !DILocation(line: 157, column: 12, scope: !163)
!170 = !DILocation(line: 158, column: 3, scope: !163)
!171 = !DILocation(line: 161, column: 7, scope: !172)
!172 = distinct !DILexicalBlock(scope: !4, file: !1, line: 161, column: 6)
!173 = !DILocation(line: 161, column: 10, scope: !172)
!174 = !DILocation(line: 161, column: 18, scope: !172)
!175 = !DILocation(line: 161, column: 16, scope: !172)
!176 = !DILocation(line: 161, column: 25, scope: !172)
!177 = !DILocation(line: 161, column: 6, scope: !4)
!178 = !DILocation(line: 163, column: 7, scope: !179)
!179 = distinct !DILexicalBlock(scope: !180, file: !1, line: 163, column: 7)
!180 = distinct !DILexicalBlock(scope: !172, file: !1, line: 161, column: 31)
!181 = !DILocation(line: 163, column: 10, scope: !179)
!182 = !DILocation(line: 163, column: 16, scope: !179)
!183 = !DILocation(line: 163, column: 7, scope: !180)
!184 = !DILocation(line: 164, column: 22, scope: !179)
!185 = !DILocation(line: 168, column: 8, scope: !179)
!186 = !DILocation(line: 169, column: 25, scope: !179)
!187 = !DILocation(line: 169, column: 34, scope: !179)
!188 = !DILocation(line: 169, column: 37, scope: !179)
!189 = !DILocation(line: 169, column: 8, scope: !179)
!190 = !DILocation(line: 170, column: 25, scope: !179)
!191 = !DILocation(line: 170, column: 34, scope: !179)
!192 = !DILocation(line: 170, column: 8, scope: !179)
!193 = !DILocation(line: 164, column: 4, scope: !179)
!194 = !DILocation(line: 171, column: 3, scope: !180)
!195 = !DILocation(line: 171, column: 6, scope: !180)
!196 = !DILocation(line: 171, column: 12, scope: !180)
!197 = !DILocation(line: 172, column: 3, scope: !180)
!198 = !DILocation(line: 174, column: 2, scope: !4)
!199 = !DILocation(line: 175, column: 1, scope: !4)
!200 = !DILocalVariable(name: "m", arg: 1, scope: !108, file: !1, line: 90, type: !13)
!201 = !DILocation(line: 90, column: 35, scope: !108)
!202 = !DILocation(line: 92, column: 10, scope: !108)
!203 = !DILocation(line: 92, column: 2, scope: !108)
!204 = !DILocation(line: 93, column: 28, scope: !205)
!205 = distinct !DILexicalBlock(scope: !108, file: !1, line: 92, column: 13)
!206 = !DILocation(line: 94, column: 27, scope: !205)
!207 = !DILocation(line: 95, column: 33, scope: !205)
!208 = !DILocation(line: 96, column: 32, scope: !205)
!209 = !DILocation(line: 97, column: 28, scope: !205)
!210 = !DILocation(line: 98, column: 13, scope: !205)
!211 = !DILocation(line: 100, column: 1, scope: !108)
!212 = !DILocalVariable(name: "m", arg: 1, scope: !111, file: !1, line: 51, type: !78)
!213 = !DILocation(line: 51, column: 20, scope: !111)
!214 = !DILocalVariable(name: "s", scope: !111, file: !1, line: 53, type: !43)
!215 = !DILocation(line: 53, column: 9, scope: !111)
!216 = !DILocation(line: 53, column: 20, scope: !111)
!217 = !DILocation(line: 53, column: 13, scope: !111)
!218 = !DILocalVariable(name: "written", scope: !111, file: !1, line: 54, type: !36)
!219 = !DILocation(line: 54, column: 10, scope: !111)
!220 = !DILocation(line: 56, column: 2, scope: !111)
!221 = !DILocation(line: 56, column: 9, scope: !222)
!222 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 1)
!223 = !DILocation(line: 56, column: 11, scope: !222)
!224 = !DILocation(line: 56, column: 2, scope: !222)
!225 = !DILocation(line: 57, column: 22, scope: !226)
!226 = distinct !DILexicalBlock(scope: !111, file: !1, line: 56, column: 16)
!227 = !DILocation(line: 57, column: 32, scope: !226)
!228 = !DILocation(line: 57, column: 25, scope: !226)
!229 = !DILocation(line: 57, column: 13, scope: !230)
!230 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 1)
!231 = !DILocation(line: 57, column: 11, scope: !226)
!232 = !DILocation(line: 58, column: 7, scope: !233)
!233 = distinct !DILexicalBlock(scope: !226, file: !1, line: 58, column: 7)
!234 = !DILocation(line: 58, column: 15, scope: !233)
!235 = !DILocation(line: 58, column: 7, scope: !226)
!236 = !DILocation(line: 59, column: 4, scope: !233)
!237 = !DILocation(line: 60, column: 8, scope: !226)
!238 = !DILocation(line: 60, column: 5, scope: !226)
!239 = !DILocation(line: 61, column: 8, scope: !226)
!240 = !DILocation(line: 61, column: 5, scope: !226)
!241 = !DILocation(line: 56, column: 2, scope: !242)
!242 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 2)
!243 = !DILocation(line: 63, column: 1, scope: !111)
!244 = !DILocation(line: 72, column: 2, scope: !114)
!245 = !DILocation(line: 73, column: 1, scope: !114)
!246 = !DILocalVariable(name: "buff", arg: 1, scope: !117, file: !1, line: 104, type: !93)
!247 = !DILocation(line: 104, column: 24, scope: !117)
!248 = !DILocalVariable(name: "states", arg: 2, scope: !117, file: !1, line: 104, type: !13)
!249 = !DILocation(line: 104, column: 43, scope: !117)
!250 = !DILocalVariable(name: "lowbit", scope: !117, file: !1, line: 106, type: !13)
!251 = !DILocation(line: 106, column: 15, scope: !117)
!252 = !DILocation(line: 108, column: 2, scope: !117)
!253 = !DILocation(line: 108, column: 10, scope: !117)
!254 = !DILocation(line: 111, column: 2, scope: !117)
!255 = !DILocation(line: 111, column: 19, scope: !256)
!256 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 1)
!257 = !DILocation(line: 111, column: 34, scope: !256)
!258 = !DILocation(line: 111, column: 33, scope: !256)
!259 = !DILocation(line: 111, column: 31, scope: !256)
!260 = !DILocation(line: 111, column: 26, scope: !256)
!261 = !DILocation(line: 111, column: 17, scope: !256)
!262 = !DILocation(line: 111, column: 43, scope: !256)
!263 = !DILocation(line: 111, column: 2, scope: !256)
!264 = !DILocation(line: 112, column: 14, scope: !265)
!265 = distinct !DILexicalBlock(scope: !117, file: !1, line: 111, column: 49)
!266 = !DILocation(line: 112, column: 13, scope: !265)
!267 = !DILocation(line: 112, column: 10, scope: !265)
!268 = !DILocation(line: 113, column: 10, scope: !265)
!269 = !DILocation(line: 113, column: 27, scope: !265)
!270 = !DILocation(line: 113, column: 16, scope: !265)
!271 = !DILocation(line: 113, column: 3, scope: !272)
!272 = !DILexicalBlockFile(scope: !265, file: !1, discriminator: 1)
!273 = !DILocation(line: 114, column: 7, scope: !274)
!274 = distinct !DILexicalBlock(scope: !265, file: !1, line: 114, column: 7)
!275 = !DILocation(line: 114, column: 14, scope: !274)
!276 = !DILocation(line: 114, column: 7, scope: !265)
!277 = !DILocation(line: 115, column: 11, scope: !274)
!278 = !DILocation(line: 115, column: 4, scope: !274)
!279 = !DILocation(line: 111, column: 2, scope: !280)
!280 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 2)
!281 = !DILocation(line: 117, column: 9, scope: !117)
!282 = !DILocation(line: 117, column: 2, scope: !117)
!283 = !DILocalVariable(name: "s", arg: 1, scope: !120, file: !1, line: 76, type: !13)
!284 = !DILocation(line: 76, column: 21, scope: !120)
!285 = !DILocation(line: 78, column: 10, scope: !120)
!286 = !DILocation(line: 78, column: 2, scope: !120)
!287 = !DILocation(line: 79, column: 27, scope: !288)
!288 = distinct !DILexicalBlock(scope: !120, file: !1, line: 78, column: 13)
!289 = !DILocation(line: 80, column: 29, scope: !288)
!290 = !DILocation(line: 81, column: 27, scope: !288)
!291 = !DILocation(line: 82, column: 27, scope: !288)
!292 = !DILocation(line: 83, column: 29, scope: !288)
!293 = !DILocation(line: 84, column: 28, scope: !288)
!294 = !DILocation(line: 85, column: 13, scope: !288)
!295 = !DILocation(line: 87, column: 1, scope: !120)
